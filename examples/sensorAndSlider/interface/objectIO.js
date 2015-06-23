// code for communication
function HybridObject () {
    this.object = io.connect();

    this.write = function(IO, value, mode)
    { 
    	if(!mode) mode = "f";
    	this.object.emit('object', JSON.stringify({pos:IO, obj:objectExp.obj, value:value , mode: mode})); };

    this.readRequest =  function(IO) {
        this.object.emit('/object/value', JSON.stringify({pos:IO, obj:objectExp.obj}));};

    this.read =  function(IO, data) {
        if(data.pos === IO)
            return data.value;};
}
