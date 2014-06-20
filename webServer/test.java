import java.io.File;
import java.net.InetAddress;
import java.net.UnknownHostException;
import java.net.NetworkInterface;
import java.util.Enumeration;

public class test {
	public static void main(String[] args) throws Exception {
		//String str = System.getenv("WEB_ROOT");
		//System.out.println(str);
		//byte -128~127
		//byte key = 0x9d;
		//int num = 0x9d;
		//System.out.println(key);
		//System.out.println(num);

		//InetAddress local = InetAddress.getLocalHost();
		//System.out.println(local.getHostAddress());

		Enumeration<NetworkInterface> e = NetworkInterface.getNetworkInterfaces();
		InetAddress ip = null;
		boolean quit = false;
    	while(e.hasMoreElements() && !quit)
    	{
			NetworkInterface net = e.nextElement();
			if(net.isUp()) {
				System.out.println(net.getDisplayName());
				Enumeration<InetAddress> addr = net.getInetAddresses();

				while(addr.hasMoreElements()) {
					ip = addr.nextElement();
					if( !ip.isSiteLocalAddress()
							&& !ip.isLoopbackAddress()
							&& ip.getHostAddress().indexOf(":") == -1) {
						System.out.println("\t" + ip.getHostAddress());
						//quit = true;
						break;
					} else if( ip.isSiteLocalAddress()
							&& !ip.isLoopbackAddress()
							&& ip.getHostAddress().indexOf(":") == -1) {
						System.out.println("\t" + ip.getHostAddress());
					}
				}
			}
    	}

	}
}
