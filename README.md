# LeftRightImageSplitter

## Usage

Create a file named `example.txt` including all file names you want to split. For example:

  a.jpg
  aa.jpg

Then create two folders named `left` and `right` and execute:

`./LeftRightImageSplitter < example.txt`

And you will get splitted images in `left/%d.jpg` and `right/%d.jpg`.
