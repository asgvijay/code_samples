var express = require("express");
var app = express();
var path = require('path');
app.use(express.static('views'));
//Store all HTML files in view folder.
app.use(express.static(__dirname + '/public'));

//Store all JS and CSS in public folder.

app.set('port', 7171);


app.get('/',function(req,res){
  res.sendFile(__dirname + '/views/gameStateDemo.html');
});


app.listen(app.get('port'), function(){
  console.log('Express started on http://localhost:' + app.get('port') + '; press Ctrl-C to terminate.');
});