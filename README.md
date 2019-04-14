# Lit Synaptix

### The Process
##### Setting up the Muse Headset
For this project, we used the 2016 Muse Headset and the sample TestLibMuseAndroid app, which you can find 
[here](http://developer.choosemuse.com/sdk/android/getting-started-with-libmuse-android). Follow the guide to download Android Studio and run the app on your Android device. Make sure the Muse headset is on (the light should be on but not solid) and press refresh in the app. Once the device shows up, select it and press connect. Note that you should not connect the Muse headset directly to your phone via bluetooth connection; the app does that for you.

### Setting Up Firebase
Go to the [Firebase website](firebase.google.com) and set up your own Firebase Realtime Database. Near the top, you will see a link with the format https://example.firebaseio.com/. This is the hostname of the realtime database, and you will need it later to connect your Wifi module to Firebase. Under data, add a child with value false. We decided to call the child corresponding to our device LED1 and nested it under a child called devices. 

##### Modifying the Muse App
The first thing that you will need to do is connect your app to Firebase. In Android Studio, go to Tools > Firebase > Realtime Database and follow the instructions there to connect your app to Firebase. Once the app has been connected, add the following lines to the top of `MainActivity`.

```
DatabaseReference databaseRef = FirebaseDatabase.getInstance().getReference();
DatabaseReference LED1 = databaseRef.child(“devices”).child(“LED1”);
```
**Note that LED1 will differ based on how you nested your children.** 
Above the `receiveMuseDataPacket` function, place this function:

```
private void determineDeviceState(double [] aBuffer, double aThreshold)
{
   double totalAlpha = 0;
   for (int i = 0; i < aBuffer.length; i++)
       totalAlpha += aBuffer[i];
   double avgAlpha = totalAlpha/aBuffer.length;
   if (avgAlpha > aThreshold) {
       LED1.setValue(true);
   }
   else if (avgAlpha <= aThreshold) {
       LED1.setValue(false);
   }
}
```
After that, all you need to do is call the function under `case ALPHA_RELATIVE:` in `receiveMuseDataPacket`: `determineDeviceStatement(alphaBuffer, threshold)`, where `threshold` is a double between 0 and 1. We chose 0.2 as our threshold, but you can adjust it depending on how responsive you want your devices to be.

