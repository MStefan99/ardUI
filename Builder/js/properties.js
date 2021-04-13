'use strict';


addEventListener('load', () => {
	const form = document.getElementById('res-form');
	const canvas = document.getElementById('builder-canvas');
	const resList = document.getElementById('res-list');
	const resetButton = document.getElementById('res-reset');
	const flipButton = document.getElementById('res-flip');
	const params = new URLSearchParams(location.search);


	form['res-width'].value = params.get('width') || canvas.width;
	form['res-height'].value = params.get('height') || canvas.height;

	resetButton.addEventListener('click', () => {
		window.location.search = '';
	});


	flipButton.addEventListener('click', () => {
		const width = form['res-width'].value;
		const height = form['res-height'].value;

		form['res-height'].value = width;
		form['res-width'].value = height;
	});


	resList.addEventListener('change', e => {
		const option = resList.selectedOptions[0];
		form['res-width'].value = option.getAttribute('data-w');
		form['res-height'].value = option.getAttribute('data-h');
	});


	form.addEventListener('submit', e => {
		e.preventDefault();
		const width = form['res-width'].value;
		const height = form['res-height'].value;

		if (!+width || !+height) {
			alert('Please check that both width and height are a number.');
			return;
		}

		params.set('width', width);
		params.set('height', height);
		window.location.search = params;
	});
});
