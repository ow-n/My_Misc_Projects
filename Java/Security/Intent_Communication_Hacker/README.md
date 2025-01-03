## Android Intent Security

This program demonstrates how different applications can read data sent between applications. So we fixed this security concern by implementing a simple cipher encryption (shifting characters) to securely send the message.

- Java Intents are messaging objects. 	
  - used to request an action from another app (binding)
- Bundles are key-value pair data structures. 
  1. Create the intent
  2. Encrypt message
  3. Add message to intent by adding it to the bundle inside intent
  4. Send intent

1) Synced Sender / Receiver / HackerApp with Gradle

2) Built all applications onto emulator

3) Sender sends message, and receiver received it. 
HackerApp can intercept message since it’s using the Receiver application ID.
Message = “Message sent to Receiver: “Hello””

4. Implement cipher and decipher for sender and receiver.
Cipher implementation works by shifting the message by 42.

5. Retest applications.
Sender and Receiver can send messages fine.
But now the HackerApp receives an encrypted message instead.
Message = “Encryped Message ABCABC”
