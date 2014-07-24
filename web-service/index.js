/**
 * Created by bruno.almeida on 14/07/14.
 */
var Hapi = require('hapi');
var server = new Hapi.Server(3000);

var mongoose = require('mongoose');
mongoose.connect('mongodb://localhost/vote');

var candidate = mongoose.Schema({
    name: String,
    party: String,
    number: String
});

var db = mongoose.model('candidates', candidate);

server.route({
    method: 'GET',
    path: '/candidates',
    handler: function (request, reply) {
        db.find({},{_id:0}, function (err, result) {
                if (err) return console.error(err);
                reply(JSON.stringify(result));
        });
    }
});

server.start(function () {
    console.log('Server running at:', server.info.uri);
});