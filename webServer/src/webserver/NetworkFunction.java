package webserver;

import java.net.InetAddress;
import java.net.NetworkInterface;
import java.util.Enumeration;

public class NetworkFunction {
	public static InetAddress getIpAddress() throws Exception {
		InetAddress ip = null;

		Enumeration<NetworkInterface> e = NetworkInterface.getNetworkInterfaces();
		boolean found = false;
    	while(e.hasMoreElements() && !found)
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
						found = true;
						break;
					} else if( ip.isSiteLocalAddress()
							&& !ip.isLoopbackAddress()
							&& ip.getHostAddress().indexOf(":") == -1) {
						System.out.println("\t" + ip.getHostAddress());
					}
				}
			}
    	}
		return ip;
	}
}
