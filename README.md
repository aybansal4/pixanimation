# PixAnimation

PixAnimation is a lightweight C++ animation tool that allows you to create pixel-based animations using simple text files. It relies on frame-based pixel representation, supporting a palette of colors and flexible input file structures.

---

## ⚙️ Features

<<<<<<< HEAD
- **Extension-agnostic input:** Accepts any file extension
=======
- **Extension-agnostic input:** Accepts any file extension.  
>>>>>>> b625ce99b21f3dcba47492c25712bb5eb1360244
- **Simple syntax:** Use characters to define pixels and separate frames with `:`.  
- **Customizable FPS:** Specify frames per second in options.  
- **Output options:** Save animations as MP4 files using FFmpeg integration.  
- **C++ implementation:** Uses only the standard library, `fstream`, and FFmpeg libraries.  

---

## 🧾 File Input Rules

1. Any file extension can be used
2. Everything before the first `:` is treated as a comment, title, description, or shebang and is ignored by the parser.  
3. Frames **start after the first colon** and are separated by lines containing a single `:`.  
4. Each frame’s rows are separated by newlines.  
5. Each character represents one pixel.  
6. All frames **must have the same dimensions**.  
7. Only the following symbols are allowed (case-insensitive):

| Symbol | Color  |
|--------|--------|
| r      | Red    |
| o      | Orange |
| y      | Yellow |
| g      | Green  |
| b      | Blue   |
| v      | Violet |
| 1      | White  |
| 0      | Black  |

8. Any other character triggers an error.  

---

## 🎨 Example File

> **Tip:** For best readability, open this file in a monospaced font like **Fira Code**.

```
PixAnimation Demo - Rainbow Pulse Animation v1

:
0000000000
0000000000
0000000000
0000000000
0000000000
0000000000
0000000000
0000000000
0000000000
0000000000

:
0000000000
0000000000
0000000000
0000000000
0000000000
0000000000
0000000000
0000000000
0000000000
00000000r0

:
0000000000
0000000000
0000000000
0000000000
0000000000
0000000000
0000000000
0000000000
0000000rr0
0000000rro

:
0000000000
0000000000
0000000000
0000000000
0000000000
0000000000
0000000rr0
0000000rro
000000rroy
000000rroy
```

# PixAnimation - Credits & License

---

## 👥 Credits

- **Project Author:** [Ayan Bansal](mailto:ayanbansal4@gmail.com)  
- **C++ Implementation:** Developed using the Standard Library, `fstream`, and FFmpeg integration.  
- **Special Thanks:**  
  - FFmpeg contributors for making video handling simple and robust.  
  - Open-source communities for inspiration and support.  
- This software uses code of [FFmpeg](http://ffmpeg.org) licensed under the [LGPLv2.1](http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html) and its source can be downloaded [here](https://rawgithubusercontent.com/aybansal4/pixanimation/blob/main/pixanimation_parser.cpp).  
### ✅ Summary

PixAnimation is open for personal, educational, and commercial use, as long as credit is given and the license terms are followed. Enjoy creating pixel animations!

