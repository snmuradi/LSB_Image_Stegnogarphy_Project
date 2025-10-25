# 🖼️ LSB Image Steganography Project

## 📘 Project Overview

The **LSB (Least Significant Bit) Image Steganography** project is a C-based application that allows users to **hide secret messages within images** without visibly altering them.
It uses the least significant bit of each pixel to encode data, demonstrating basic concepts of **data hiding** and **image processing** in embedded and computer systems.

---

## 🛠️ Technologies Used

* C Programming Language
* File Handling in C (for image and message files)
* GCC Compiler / Code::Blocks / VS Code
* BMP Image Format for hiding data
* Command-Line Interface

---

## ⚙️ Features

* Encode secret messages into images using LSB technique.
* Decode hidden messages from steganographic images.
* Supports text-based messages of varying lengths.
* Works with standard BMP image files.
* Provides error handling for invalid input or unsupported files.

---

## 🚧 Key Challenges

* Understanding the BMP image file structure to manipulate pixel data.
* Converting messages into binary format and embedding them correctly.
* Ensuring the image quality remains visually unchanged after embedding.
* Handling different image sizes and ensuring message fits the image.
* Debugging file reading/writing and bit manipulation logic.

---

## 🎯 Learnings

* Learned to manipulate image pixels at the bit level.
* Gained hands-on experience in **file handling** for binary files in C.
* Understood the principles of **steganography** and secure data hiding.
* Improved skills in **bitwise operations** and **data encoding/decoding**.
* Developed logical thinking for embedding and extracting messages accurately.

---

## 👨‍💻 Developer

**Sharookh Najeersab Muradi**
B.Tech in Electronics and Communication Engineering
Gitam University, Bengaluru

---

## 🧠 Conclusion

This project demonstrates how digital images can be used to hide confidential information using LSB steganography.
It provides practical understanding of bit-level operations, file handling, and secure data storage techniques.
