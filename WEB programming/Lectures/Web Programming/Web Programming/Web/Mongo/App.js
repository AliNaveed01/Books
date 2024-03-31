var http=require('http');
var app=require('mongodb').MongoClient;
var url="mongodb://127.0.0.1:27017/"

app.connect(url,function(err,db){
    if (err) throw err;
    console.log("Connected!");
    var dbo=db.db("Books");
    http.createServer(function(req,res){
        var obj={
                    title:req.body.title,
                    genre:req.body.genre,
                    author:req.body.author
                };
        dbo.collection("book").insertOne(obj,function(err,res){
            console.log("Inserted!");
            db.close();
        })
        res.write("Hello world!");
        res.end();
    }).listen(8080);
});
