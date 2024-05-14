# RC4
This is a simple implementation of the RC4 symmetric encryption algorithm in C++. The program allows for both encryption and decryption using the same key. The input can be either plain byte storage or Base64 encoded.The output can be Base64 encoded.

## Usage
Upon running the program, you will encounter the following prompts:

1. Select Operation Mode:
Enter 0 for encryption.
Enter 1 for decryption.
2. Input Format (for encryption only):
Enter 0 if your plaintext is in byte storage (typical one byte per character storage).
Enter 1 if your plaintext is in Base64 encoded format.
3.Input Plaintext or Ciphertext:
For encryption, enter the plaintext as instructed.
For decryption, enter the Base64 encoded ciphertext.
4.Input the Key:
Enter a key that will be used for both encryption and decryption. The key is treated as byte storage.
5.Output
For encryption, the program outputs the ciphertext in Base64 encoding.
For decryption, the program outputs the decrypted plaintext in both regular and Base64 encoded formats.

### Example


## Contributing
Contributions are welcome!

You can help by:

- Reporting issues
- Suggesting improvements
- Adding new features through pull requests

## License
This project is licensed under the MIT License.

