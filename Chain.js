var fs = require('fs');
const http = require('http');

function readModuleFile(path, callback) {
    try {
        var filename = require.resolve(path);
        fs.readFile(filename, 'utf8', callback);
    } catch (e) {
        callback(e);
    }
}

let raw="";
let out = [];
readModuleFile('./Blockchain.txt', function (err, words) {
    if(err){
        console.log("Couldn't read file");
        console.log(err);
    }
    else
    {
        raw = words;

        raw = raw.split('\r\n');
        

        let isBlock = false;
        let isTransaction = false;
        let blockC = 0;
        let transactionC=0;
        for(let i =0;i<raw.length;i++)
        {
            raw[i] = raw[i].replace('\t','');
            raw[i] = raw[i].replace('\t','');
        }
        //console.log(raw);
        for(let i =0;i<raw.length;i++)
        {
            //console.log(out + " b:" + isBlock + " t:"+isTransaction);
            if(raw[i]=="{" && !isBlock)
            {
                isBlock=true;
                
            }
            else if(raw[i]=="{" && isBlock)
            {
                isTransaction=true;
                
            }
            else if(raw[i]=="}" && isTransaction)
            {
                isTransaction=false;
                transactionC++;
                
            }
            else if(raw[i]=="}" && !isTransaction)
            {
                isBlock=false;
                blockC++;
                transactionC=0;
                
            }
            else if(isBlock && !isTransaction)
            {
                out.push({});
                out[blockC]["Prevhash"] = raw[i].toString();
                i++;
                //console.log(raw[i] + " " + i);
                out[blockC]["Timestamp"] = raw[i];
                i++
                out[blockC]["Version"] = raw[i];
                i++
                out[blockC]["MerkleRoot"] = raw[i];
                i++
                out[blockC]["Difficulty"] = raw[i];
                i++;
                out[blockC]["Noncec"] = raw[i];
                out[blockC]["Transactions"] = [];
                //console.log(raw[i]);

            }
            else if(isBlock===true && isTransaction===true)
            {
                //console.log(out);
                out[blockC]["Transactions"].push({});
                //console.log(transactionC);
                out[blockC]["Transactions"][transactionC]["Hash"] = raw[i];
                //console.log(out);
                i++;
                out[blockC]["Transactions"][transactionC]["Timestamp"] = raw[i];
                i++;
                out[blockC]["Transactions"][transactionC]["Sender"] =raw[i];
                i++;
                out[blockC]["Transactions"][transactionC]["Reciever"] = raw[i];
                i++;
                out[blockC]["Transactions"][transactionC]["Amount"] = raw[i];
            }
        }
        out = JSON.stringify(out);
        //console.log(out);
        StartServer();
    }
    //console.log(words);
});


function StartServer()
{



const hostname = '127.0.0.1';

const port = 3000;

let htmltxt = `<!DOCTYPE html><html lang="en"><head><meta charset="UTF-8"><meta http-equiv="X-UA-Compatible" content="IE=edge"><meta name="viewport" content="width=device-width, initial-scale=1.0"><title>Memes debug</title></head><body>F12 and check console<script>let print2 = ${out};console.log(print2);</script></body></html>`;

const server = http.createServer(function(req, res) {

  res.statusCode = 200;

  res.setHeader('Content-Type', 'text/html');

  res.write(htmltxt);
  res.end();

});


server.listen(port, hostname, function() {

  console.log('Server running at http://'+ hostname + ':' + port + '/');

});
}