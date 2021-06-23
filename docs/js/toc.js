'use strict';


addEventListener('load', () => {
	const tocContainer = document.getElementById('toc-container');
	const tocTargets = document.getElementsByClassName('toc');

	if (!tocContainer) {
		throw new Error('No TOC Container found!');
	}

	for (const element of tocTargets) {
		if (!element.id) {
			element.id = 'toc-' + Math.floor(Math.random() * 1000000);
		}

		const tocElement = document.createElement('a');
		tocElement.href = '#' + element.id;
		tocElement.classList.add(element.tagName);
		tocElement.innerText = element.innerText;

		tocContainer.appendChild(tocElement);
	}
});