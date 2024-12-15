const express = require('express');
const http = require('http');
const path = require('path');
const socketio = require('socket.io');
const app = express();
const server = http.createServer(app);
const io = socketio(server);
app.set("view engine", "ejs");
app.set(express.static(path.join(__dirname,"public")));
io.on("connection",(socket)=>{
    socket.on("send-location",(data)=>{
        console.log("location send")
        io.emit("receive-location",{ id: socket.id, ...data});
    });
    socket.on("disconnect", ()=>{
        io.emit("user-disconnected", socket.id);
        console.log("user disconnected")
    })
    console.log("connected");
});
app.get("/",(req,res)=>{
res.render("index");
console.log("Server running on port 3000");
})
server.listen(3003);