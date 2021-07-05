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
	if (['CODE', 'PRE'].includes(element.tagName)) {
		// skipping code blocks
	} else if (['P', 'SPAN'].includes(element.tagName)) {  // TODO: find a better solution for iterating
		element.innerHTML = element.innerHTML.split(/(\W)/).map(word =>
				keywords.has(word) ? `<a href="${keywords.get(word)}" class="auto-reference">${word}</a>` : word).join('');
	} else {
		for (const child of element.children) {
			reference(child);
		}
	}
}


addEventListener('load', () => {
	reference(document.querySelector('article'));
});
