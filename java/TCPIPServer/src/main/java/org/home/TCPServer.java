package org.home;

import java.io.*;
//import java.util.*;
import java.net.*;

public class TCPServer {
	
//	private static Vector<Session> sessions;

	public static void main(String[] args) {
			try {
				System.out.println("Hello World!!1" );
				ServerSocket welcomeSocket = new ServerSocket( 45070 );
				boolean stop = false;
				while(!stop) {
					new Session(welcomeSocket.accept()).start();
					System.out.println("add session.");
				}
				welcomeSocket.close();
			} catch( IOException e ) {
				e.printStackTrace();
			}
		System.out.println("Leave program.");
	}

	private static class Session extends Thread {
		private Socket socket;	

		public Session( Socket s ) {
			socket = s;
		}

		@Override
		public void run()
		{
			try {
				BufferedReader in =
						new BufferedReader(new InputStreamReader(socket.getInputStream()));
				DataOutputStream out = new DataOutputStream(socket.getOutputStream());
				for (;;) {
					String str = in.readLine();
					if(str == null || str.equals("."))
						break;
					out.writeBytes(str.toUpperCase());
				}
			}
			catch (IOException e) {
				log( "Error handling client: " + e );
			}
			finally {
				try {
					socket.close();
				}
				catch (IOException e) {
					log("Couldn't close a socket, what's going on?");
				}
				log("Connection with client closed.");
			}

		}

		private void log(String message) {
			System.out.println(message);
		}

	};
};
