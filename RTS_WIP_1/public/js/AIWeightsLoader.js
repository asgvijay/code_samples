var aiWeights = null;

var loadNormal = function() {
	var request = new XMLHttpRequest();
	request.open('GET', '/jsonFiles/weights.json', true);
	request.onload = function() {
		easyWeights = JSON.parse(this.responseText);
		if (aiWeights == null){
			console.log('this means the default weights should load');
			aiWeights = JSON.parse(this.responseText);
		}
		
		console.log(easyWeights);
		console.log('first', aiWeights);
	};
	request.send();
};

aiWeights = localStorage.getItem('aiweights');
console.log('trying to laod the aiweights locally');
console.log(aiWeights);

loadNormal();


