'use strict';


addEventListener('load', () => {
	const form = document.getElementById('dim-form');
	const resetButton = document.getElementById('dim-reset');
	const canvas = document.getElementById('builder-canvas');
	const params = new URLSearchParams(location.search);


	form['dim-width'].value = params.get('width') || canvas.width;
	form['dim-height'].value = params.get('height') || canvas.height;

	resetButton.addEventListener('click', () => {
		window.location.search = '';
	});


	form.addEventListener('submit', e => {
		e.preventDefault();
		const width = form['dim-width'].value;
		const height = form['dim-height'].value;

		if (!+width || !+height) {
			alert('Please check that both width and height are a number.');
			return;
		}

		params.set('width', width);
		params.set('height', height);
		window.location.search = params;
	});
});
