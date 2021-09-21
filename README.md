# MediaPipeOSC

The Python script `mediapipe_osc_server.py` runs the [MediaPipe Holistic model](https://google.github.io/mediapipe/solutions/holistic) and send its results through OSC. You will need to install the Python MediaPipe API following the [official guide](https://google.github.io/mediapipe/getting_started/python.html) (I've tested it using Python 3.9.1) and the [python-osc](https://pypi.org/project/python-osc/) package.

Some comments about the `mediapipe_osc_server.py` script:

1. It sends the OSC messages to the localhost through the port 8000, you can change it in [line 21](https://github.com/DavidDiazGuerra/MediaPipeOSC/blob/568584a02ed4454d76baf05e73889e80b2fa1f91/mediapipe_osc_server.py#L21)
2. It flips the input image before sending it to the model, which is nice when visualizing a selfie camera but makes the model get right and left mixed up. If you want to avoid it, just comment [line 35](https://github.com/DavidDiazGuerra/MediaPipeOSC/blob/568584a02ed4454d76baf05e73889e80b2fa1f91/mediapipe_osc_server.py#L35).
3. If you have several video capture devices you can choose which one you want to use in [line 23](https://github.com/DavidDiazGuerra/MediaPipeOSC/blob/568584a02ed4454d76baf05e73889e80b2fa1f91/mediapipe_osc_server.py#L23)

`exampleOF_MediaPipeOSC` is a simple [openframeworks](openframeworks.cc) example about how to read the OSC messages with the MediaPipe results to develop interactive applications. It needs the ofxOSC addon, which is included with the official installation.
