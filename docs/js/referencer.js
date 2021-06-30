'use strict';

const keywords = new Map();
keywords.set('Activity', '/pages/reference/Activity');
keywords.set('ActivityManager', '/pages/reference/ActivityManager');
keywords.set('ActivitySwitcher', '/pages/reference/ActivitySwitcher');
keywords.set('Adapter', '/pages/reference/Adapter');
keywords.set('AdapterView', '/pages/reference/AdapterView');
keywords.set('ArrayAdapter', '/pages/reference/ArrayAdapter');
keywords.set('Bundle', '/pages/reference/Bundle');
keywords.set('ButtonView', '/pages/reference/ButtonView');
keywords.set('ConstraintLayout', '/pages/reference/ConstraintLayout');
keywords.set('Drawable', '/pages/reference/Drawable');
keywords.set('Event', '/pages/reference/Event');
keywords.set('EventManager', '/pages/reference/EventManager');
keywords.set('less', '/pages/reference/less');
keywords.set('LinearLayout', '/pages/reference/LinearLayout');
keywords.set('ListView', '/pages/reference/ListView');
keywords.set('ProgressBar', '/pages/reference/ProgressBar');
keywords.set('Rect', '/pages/reference/Rect');
keywords.set('Singleton', '/pages/reference/Singleton');
keywords.set('TextView', '/pages/reference/TextView');
keywords.set('View', '/pages/reference/View');
keywords.set('ViewGroup', '/pages/reference/ViewGroup');


function reference(element) {
	if (element.children.length) {
		for (const child of element.children) {
			if (child.tagName !== 'CODE') {
				reference(child);
			}
		}
	} else {
			element.innerHTML = element.innerText.split(/(\W)/).map(word =>
					keywords.has(word) ? `<a href="${keywords.get(word)}" class="auto-reference">${word}</a>` : word).join('');
	}
}


addEventListener('load', () => {
	reference(document.documentElement);
});
