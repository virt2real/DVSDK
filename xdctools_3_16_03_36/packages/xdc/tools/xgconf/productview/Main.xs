function run( cmdr, args )
{
	var h = new java.util.HashMap();
    
    for(var i = 0;i < args.length;i++) {
    	var prodView = _getProductView(args[i]);
    	h.put(args[i],prodView);
    }
    
    var socket = cmdr.socket;

    socket.giveToClient(h);
}


function _getProductView(productViewModule) {
	try {
	    var productView = xdc.useModule(productViewModule);
	    
	    var desc = productView.getProductDescriptor();
	    
	    var prodDescRoot = _traverseProductTree(desc, productView.$package.packageBase);
	    
	    return prodDescRoot;
	} catch (e) {
	    /* Return evaluation error */ 
	    return e.toString();
	}      

}

function _traverseProductTree(prodDesc, packageBase)
{
    var p = new xdc.jre.org.eclipse.rtsc.xdctools.model.elements.ProductDescriptor(
        prodDesc.elemName,prodDesc.moduleName, packageBase + prodDesc.iconFileName
    );
    
    if (prodDesc.elemArray != null) {
        for(var i = 0;i < prodDesc.elemArray.length; i++) {
           p.addProductDescriptor(_traverseProductTree(prodDesc.elemArray[i],packageBase));
        }
    }
    
    return p;
}
