public class main {
	static {
		try {
    		System.load("/home/akshay/workspace/test/jni/libhello.so");
    	} catch (UnsatisfiedLinkError e) {
    		System.err.println("Native code library failed to load.\n" + e);
    		System.exit(1);
    	}   
	}

	public static void main(String argv[]) {
		example.bluescape_getInfo(0);
		example.bluescape_connect(0);
		example.bluescape_status(0);
		example.bluescape_moveRight(0);
		example.bluescape_close(0);
	}
}
