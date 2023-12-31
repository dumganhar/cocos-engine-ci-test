/**
 Licensed to the Apache Software Foundation (ASF) under one
 or more contributor license agreements.  See the NOTICE file
 distributed with this work for additional information
 regarding copyright ownership.  The ASF licenses this file
 to you under the Apache License, Version 2.0 (the
 'License'); you may not use this file except in compliance
 with the License.  You may obtain a copy of the License at
 http://www.apache.org/licenses/LICENSE-2.0
 Unless required by applicable law or agreed to in writing,
 software distributed under the License is distributed on an
 'AS IS' BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 KIND, either express or implied.  See the License for the
 specific language governing permissions and limitations
 under the License.
 */

{
    function merge_obj(obj, secondObj) {
        if (!obj)
            return secondObj;

        for(var i in secondObj)
            obj[i] = merge_obj(obj[i], secondObj[i]);

        return obj;
    }
}

/*
 *  Project: point of entry from pbxproj file
 */
Project
  = headComment:SingleLineComment? InlineComment? _ obj:Object NewLine _
    {
        var proj = Object.create(null)
        proj.project = obj

        if (headComment) {
            proj.headComment = headComment
        }

        return proj;
    }

/*
 *  Object: basic hash data structure with Assignments
 */
Object
  = "{" obj:(AssignmentList / EmptyBody) "}"
    { return obj }

EmptyBody
  = _
    { return Object.create(null) }

AssignmentList
  = _ list:((a:Assignment / d:DelimitedSection) _)+
    {
        var returnObject = list[0][0];
        for(var i = 1; i < list.length; i++){
            var another = list[i][0];
            returnObject = merge_obj(returnObject, another);
        }
        return returnObject;
    }

/*
 *  Assignments
 *  can be simple "key = value"
 *  or commented "key /* real key * / = value"
 */
Assignment
  = SimpleAssignment / CommentedAssignment

SimpleAssignment
  = id:Identifier _ "=" _ val:Value ";"
    {
      var result = Object.create(null);
      result[id] = val
      return result
    }

CommentedAssignment
  = commentedId:CommentedIdentifier _ "=" _ val:Value ";"
    {
        var result = Object.create(null),
            commentKey = commentedId.id + '_comment';

        result[commentedId.id] = val;
        result[commentKey] = commentedId[commentKey];
        return result;

    }
    /
    id:Identifier _ "=" _ commentedVal:CommentedValue ";"
    {
        var result = Object.create(null);
        result[id] = commentedVal.value;
        result[id + "_comment"] = commentedVal.comment;
        return result;
    }

CommentedIdentifier
  = id:Identifier _ comment:InlineComment
    {
        var result = Object.create(null);
        result.id = id;
        result[id + "_comment"] = comment.trim();
        return result
    }

CommentedValue
  = literal:Value _ comment:InlineComment
    {
        var result = Object.create(null)
        result.comment = comment.trim();
        result.value = literal.trim();
        return result;
    }

InlineComment
  = InlineCommentOpen body:[^*]+ InlineCommentClose
    { return body.join('') }

InlineCommentOpen
  = "/*"

InlineCommentClose
  = "*/"

/*
 *  DelimitedSection - ad hoc project structure pbxproj files use
 */
DelimitedSection
  = begin:DelimitedSectionBegin _ fields:(AssignmentList / EmptyBody) _ DelimitedSectionEnd
    {
        var section = Object.create(null);
        section[begin.name] = fields

        return section
    }

DelimitedSectionBegin
  = "/* Begin " sectionName:Identifier " section */" NewLine
    { return { name: sectionName } }

DelimitedSectionEnd
  = "/* End " sectionName:Identifier " section */" NewLine
    { return { name: sectionName } }

/*
 * Arrays: lists of values, possible wth comments
 */
Array
  = "(" arr:(ArrayBody / EmptyArray ) ")" { return arr }

EmptyArray
  = _ { return [] }

ArrayBody
  = _ head:ArrayEntry _ tail:ArrayBody? _
    {
        if (tail) {
            tail.unshift(head);
            return tail;
        } else {
            return [head];
        }
    }

ArrayEntry
  = SimpleArrayEntry / CommentedArrayEntry

SimpleArrayEntry
  = val:Value EndArrayEntry { return val }

CommentedArrayEntry
  = val:Value _ comment:InlineComment EndArrayEntry
    {
        var result = Object.create(null);
        result.value = val.trim();
        result.comment = comment.trim();
        return result;
    }

EndArrayEntry
  = "," / _ &")"

/*
 *  Identifiers and Values
 */
Identifier
  = id:[A-Za-z0-9_.]+ { return id.join('') }
  / QuotedString

Value
  = Object / Array / NumberValue / StringValue

NumberValue
  = DecimalValue / IntegerValue

DecimalValue
  = decimal:(IntegerValue "." IntegerValue)
    {
        // store decimals as strings
        // as JS doesn't differentiate bw strings and numbers
        return decimal.join('')
    }

IntegerValue
  = !Alpha number:Digit+ !NonTerminator
    { return parseInt(number.join(''), 10) }

StringValue
 = QuotedString / LiteralString

QuotedString
 = DoubleQuote str:QuotedBody DoubleQuote { return '"' + str + '"' }

QuotedBody
 = str:NonQuote+ { return str.join('') }

NonQuote
  = EscapedQuote / !DoubleQuote char:. { return char }

EscapedQuote
  = "\\" DoubleQuote { return '\\"' }

LiteralString
  = literal:LiteralChar+ { return literal.join('') }

LiteralChar
  = !InlineCommentOpen !LineTerminator char:NonTerminator
    { return char }

NonTerminator
  = [^;),\n]

/*
 * SingleLineComment - used for the encoding comment
 */
SingleLineComment
  = "//" _ contents:OneLineString NewLine
    { return contents }

OneLineString
  = contents:NonLine*
    { return contents.join('') }

/*
 *  Simple character checking rules
 */
Digit
  = [0-9]

Alpha
  = [A-Za-z]

DoubleQuote
  = '"'

_ "whitespace"
  = whitespace*

whitespace
  = NewLine / [\t ]

NonLine
  = !NewLine char:Char
    { return char }

LineTerminator
  = NewLine / ";"

NewLine
    = [\n\r]

Char
  = .
