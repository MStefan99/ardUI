'use strict';

addEventListener('load', () => {
	const form = document.getElementById('res-form');
	const canvas = document.getElementById('builder-canvas');
	const resList = document.getElementById('res-list');
	const resetButton = document.getElementById('res-reset');
	const flipButton = document.getElementById('res-flip');
	const url = new URL(location.href);


	form['res-width'].value = url.searchParams.get('width') || canvas.width;
	form['res-height'].value = url.searchParams.get('height') || canvas.height;

	resetButton.addEventListener('click', () => {
		setCanvasSize();
	});


	flipButton.addEventListener('click', () => {
		// swapping width and height
		// noinspection JSSuspiciousNameCombination
		setCanvasSize(canvas.height, canvas.width);
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

		setCanvasSize(width, height);
	});


	function setCanvasSize(width, height) {
		width = width || 480;
		height = height || 320;

		url.searchParams.set('width', width);
		url.searchParams.set('height', height);
		canvas.width = +width;
		canvas.height = +height;
		history.pushState({}, "Display resize", url.toString());
		redrawDisplay();
	}
});
