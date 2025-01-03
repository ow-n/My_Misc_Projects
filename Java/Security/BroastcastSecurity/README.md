## Android Broadcast Security

**Context**: Android uses a tool called ‘WebView’ to load web content. It enables JavaScript and exposes native methods that could retrieve the user’s phone number from the JavaScript interface.

**Situation**: The JavaScript interface called ‘WebAppInterface’ was added to the WebView, which exposed the native Android methods.
There is a GetPhoneNumber() method with ‘@JavascriptInterface’ above it, allowing it to be called from any JavaScript running in WebView.

**Exploit**: If our application already gave permissions to another website to view our phone number, when we visit the hacker’s website they can also call Android.GetPhoneNumber().
This is because WebView treats all loaded web content equally.

**Solution**: To resolve this vulnerability, we add a conditional statement to ensure that only authorized websites (defined by HostingURL) can access the phone number. So the first website was given access, but when the hacker website tries to request our number, it returns Null.

---

1) Build BroadcastApp and BroadcastAttack.
BroadcastAttack receives the username broadcast from BroadcastApp.

2) Add an explicit receiver to the intent.
Instead of broadcasting to potential receiver, I ensure it only goes to intended receiver instead.

3) Define custom permissions and require receivers to have this permission to receive the broadcast. 

4) Now the Broadcast Attacker can’t see our username.
