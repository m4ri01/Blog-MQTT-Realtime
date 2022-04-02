var mqtt;
var reconnectTimeout = 2000;
var host="192.168.10.1"; //change this
var port=9001;

function onFailure(message) {
  console.log("Connection Attempt to Host "+host+"Failed");
  setTimeout(MQTTconnect, reconnectTimeout);
    }
function onMessageArrived(msg){
  // document.getElementById("changeText").innerHTML = "<h1>"+msg.payloadString+"</h1>";
  
  out_msg="Message received "+msg.payloadString+"<br>";
  console.log(out_msg);
  if (msg.destinationName == "/data/tes"){
    var pesan = ""+msg.payloadString;
    document.getElementById("dataRealtime").innerHTML = pesan;
  }
}

 function onConnect() {
console.log("Connected ");
mqtt.subscribe("/data/#");
}

function MQTTconnect() {
console.log("connecting to "+ host +" "+ port);
var x=Math.floor(Math.random() * 10000); 
var cname="orderform-"+x;
mqtt = new Paho.MQTT.Client(host,port,cname);
var options = {
  timeout: 3,
  onSuccess: onConnect,
  onFailure: onFailure,
   };
mqtt.onMessageArrived = onMessageArrived

mqtt.connect(options); 
}
