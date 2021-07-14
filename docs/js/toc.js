'use strict';


addEventListener('load', () => {
	const tocContainer = document.getElementById('toc-container');
	const tocTargets = document.getElementsByClassName('anchor');

	{
		if (!tocContainer) {
			throw new Error('No TOC Container found!');
		}

		for (const element of tocTargets) {
			const tocElement = document.createElement('a');
			tocElement.href = '#' + element.id;
			tocElement.classList.add('toc-' + element.tagName.toLowerCase(), 'toc-element');
			tocElement.innerText = element.id.replaceAll('_', ' ');

			tocContainer.appendChild(tocElement);
		}
	}
});