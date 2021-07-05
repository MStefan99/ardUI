'use strict';


addEventListener('load', () => {
	const tocContainer = document.getElementById('toc-container');
	const tocTargets = document.querySelectorAll('[data-anchor]');


	function insertBefore(newNode, referenceNode) {
		referenceNode.parentNode.insertBefore(newNode, referenceNode);
	}


	{
		if (!tocContainer) {
			throw new Error('No TOC Container found!');
		}

		for (const element of tocTargets) {
			const id = element.getAttribute('data-anchor').replaceAll(' ', '_')
					|| 'toc-' + element.tagName.toLowerCase()
					+ Number.parseInt(element.innerText.substr(0, 16), 36);

			const tocElement = document.createElement('a');
			tocElement.href = '#' + id;
			tocElement.classList.add('toc-' + element.tagName.toLowerCase(), 'toc-element');
			tocElement.innerText = id.replaceAll('_', ' ');

			const anchor = document.createElement('div');
			anchor.classList.add('anchor');
			anchor.id = id;

			insertBefore(anchor, element);

			tocContainer.appendChild(tocElement);
		}
	}
});