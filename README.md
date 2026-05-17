# RGB Matrix with Twitch Follower Display

An ESP8266-powered 15×10 NeoPixel RGB LED matrix that displays a live rainbow animation and scrolls the name of the most recent Twitch follower across the screen.

Click the image below for a demo of the project on YouTube. 

[![Demo](https://img.youtube.com/vi/kpTbQW83jog/0.jpg)](https://youtube.com/shorts/kpTbQW83jog)

## Features

- Connects to your WiFi network on boot
- Polls the Twitch API every ~60 seconds to fetch the latest follower
- Renders a full-matrix rainbow HSV animation (150 LEDs) in real time
- Scrolls the follower's username over the animation using black text

## Hardware

| Component | Details |
|---|---|
| Microcontroller | Generic ESP8266 |
| LED Matrix | 15×10 NeoPixel (WS2812B), 150 LEDs total |
| Data pin | D3 |

## Dependencies

Install these libraries via the Arduino Library Manager:

- [Adafruit NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel)
- [Adafruit NeoMatrix](https://github.com/adafruit/Adafruit_NeoMatrix)
- [Adafruit GFX](https://github.com/adafruit/Adafruit-GFX-Library)
- [ArduinoJson](https://arduinojson.org/)
- [TwitchApi](https://github.com/witnessmenow/arduino-twitch-api) by Brian Lough
- ESP8266 board support (via Boards Manager: `http://arduino.esp8266.com/stable/package_esp8266com_index.json`)

## Configuration

Before uploading, fill in the four placeholders near the top of the sketch:

```cpp
char ssid[]     = "your_wifi_name";
char password[] = "your_wifi_password";

#define TWITCH_CLIENT_ID  "your_twitch_client_id"
#define TWITCH_LOGIN      "target_channel_username"
```

A Twitch Client ID can be obtained by registering an application at [dev.twitch.tv](https://dev.twitch.tv/).

## How It Works

Every loop iteration the matrix pixels are updated with an HSV color value derived from each pixel's (x, y) position and a global counter `i`, producing a smooth scrolling rainbow. Once per minute the sketch calls the Twitch API to get the most recent follower and stores the name in `followerName`, which is then rendered as scrolling text on top of the animation.

## Credits

Inspired by [bitluni](https://www.youtube.com/@bitluni), whose LED matrix and ESP projects were a major influence on this build.

Twitch API integration built on top of the [arduino-twitch-api](https://github.com/witnessmenow/arduino-twitch-api) library by Brian Lough.

## License

MIT
