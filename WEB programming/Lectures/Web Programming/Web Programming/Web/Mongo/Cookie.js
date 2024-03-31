const cookieParser = require("cookie-parser");
const express=require("express");
const view=require("pug");
const path=require("path");

const app=express();

app.set("views",path.join("C:\\Users\\ATOnline\\Desktop\\Web\\Mongo","views"));
app.set("view engine","pug");
app.get('/', (req, res) => {

    res.render('index', { title: 'Hey', message: 'Hello there!' })
    
    })
    
app.listen(8080, () => {
    
console.log(`Listening to requests on http://localhost:8080`);
    
});

// app.use(cookieParser());
// app.get('/',(req,res)=>{
//     res.cookie("Cookie_token_name : Testing Cookie","encrypted cookie strong value",{
//         maxAge:5000,
//         expires:new Date(),
//         secure:true,
//         httponly:true,
//         sameSite:'Lax'
//     });
//     res.send("Welcome Jee!");
//     console.log(req.cookies);
//     console.log(req.body.user);
//     console.log(req.body.password);
// }).listen(8080);