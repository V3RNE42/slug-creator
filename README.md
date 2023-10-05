# slug-creator
For 'slugifying' your texts: putting-them-into-this-format

## How It Works
1. **Fetches Text**: Grabs the last copied text from your clipboard.
2. **Transforms Text**: Alters the text by:
   - Replacing spaces and new lines with hyphens.
   - Removing special characters, keeping only alphanumeric characters.
   - Ensuring no consecutive hyphens and not ending with a hyphen.
   - Adhering to a safe length for Git branch naming.
3. **Updates Clipboard**: Replaces the original clipboard text with the transformed version.

## Usage
- **Run the Executable**: Simply execute the application whenever you need to transform clipboard text.
- **Shortcut Key**: Optionally, set a shortcut key to run the application for quick access (e.g., Ctrl + Alt + T).

## Use Case
Ideal for developers and IT professionals who often need to create standardized, clean, and compliant names for branches, files, or other entities from existing text.

## System Requirements
- Windows OS
- C++ Runtime

## Note
Ensure to verify the transformed text, especially when used in critical tasks like branch naming, to avoid any unintended issues.
