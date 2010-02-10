

lc = new LocalConnection;
lc.connect("recv");

runtests = function() {

    // This should not result in a call.
    lc.send("notaconnection", "nevercalled");

    // This should call the test1 function.
    lc.send("lc576", "test1");

    var a = 5;
    var b = false;
    var c = "A string";
    var d = new Date(0);
    var e = {};
    e.aa = 6;
    e.bb = 6;
    e.cc = 6;
    e.dd = 6;


    lc.send("lc576", "test2", a, b, c, d, e);
    
    var f = [1, "str", 6];
    
    lc.send("lc576", "test3", f);

    xml = new XML('<xml><t><t2 att="abob"><t3/></t2><t2><t3>hi</t3></t2></t></xml>');

    lc.send("lc576", "test4", xml);

    g = [];
    for (var i = 0; i < 150; ++i) {
       g.push("element" + i);
    };
    
    lc.send("lc576", "test5", g);

    lc.send("lc576", "endTests");
};

getit = function()
{
    trace("Waiting for LC-Receive to reply.");
    lc.send("lc576", "ready");
};

// Wait until receiver is ready.
id = setInterval(getit, 1000);

lc.ready = function() {
    trace("LC-Receive is ready. Running tests");
    clearInterval(id);
    runtests();
};

// Called when LC-Send has finished. Exit in 3 seconds.
lc.finished = function() {
    trace("Received finish signal from LC-Receive. Exiting in 3 seconds");
    trace("ENDOFTEST");
    setInterval(exit, 3000);
};

exit = function() {
    loadMovie ("FSCommand:quit", "");
};

stop();
