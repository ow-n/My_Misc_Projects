## Android JavaScript WebView Security

**Context**: Android uses a tool called ‘WebView’ to load web content. It enables JavaScript and exposes native methods that could retrieve the user’s phone number from the JavaScript interface.

**Situation**: The JavaScript interface called ‘WebAppInterface’ was added to the WebView, which exposed the native Android methods.
There is a GetPhoneNumber() method with ‘@JavascriptInterface’ above it, allowing it to be called from any JavaScript running in WebView.

**Exploit**: If our application already gave permissions to another website to view our phone number, when we visit the hacker’s website they can also call Android.GetPhoneNumber().
This is because WebView treats all loaded web content equally.

**Solution**: To resolve this vulnerability, we add a conditional statement to ensure that only authorized websites (defined by HostingURL) can access the phone number. So the first website was given access, but when the hacker website tries to request our number, it returns Null.

---

1) Build WebView app.
Visit https://goo.gl/TIGDOb and give it access to my phone number.

2) Visit hacker website: https://bitly.com/2sfdX0v
Hacker able to take my phone number based on the permissions already given.

3) Add a conditional to only return GetUserPhoneNumber() only if the HostingURL was authorized

4) Check now that the authorized website still can see our number while the hacker app can’t. The hacker app now says my number is undefined.
