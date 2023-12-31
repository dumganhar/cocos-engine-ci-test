const { template, $, update, close } = require('./base');

exports.template = template;
exports.$ = $;
exports.update = update;
exports.close = close;

exports.ready = function() {
    const tooltip = document.createElement('ui-tooltip');
    tooltip.setAttribute('arrow', 'top left+10px');
    this.$.componentContainer.before(tooltip);

    const label = document.createElement('ui-label');
    tooltip.appendChild(label);
    label.setAttribute('style', 'display: inline-block; padding: 10px;');
    label.setAttribute('value', 'i18n:ENGINE.components.safe_area.brief_help');
};
