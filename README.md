# system-icon

Get associated file/folder icon for Node.js.

## Installation

```bash
$ npm install --save system-icon
```

## Supported platforms

* macOS 10.6 or later
* Windows Vista or later

## Usage

Get icon for file or folder path:

```js
const {writeFileSync} = require('fs');
const {
  getIconForPath,
  ICON_SIZE_MEDIUM
} = require('system-icon');

getIconForPath("/path/to/file_or_folder", ICON_SIZE_MEDIUM, (err, result) => {
  if (err) {
    console.error(err);
  } else {
    writeFileSync("icon.png", result);
  }
});
```

Get icon for file extension:

```js
const {writeFileSync} = require('fs');
const {
  getIconForExtension,
  ICON_SIZE_MEDIUM
} = require('system-icon');

getIconForExtension(".ext", ICON_SIZE_MEDIUM, (err, result) => {
  if (err) {
    console.error(err);
  } else {
    writeFileSync("icon.png", result);
  }
});
```

## API

### Constants

#### Size constants

The correspondence between the size constants and the icon size actually obtainable on each platform is as follows:

| Constant                | Windows | macOS   |
| ----------------------- | ------- | ------- |
| `ICON_SIZE_EXTRA_SMALL` |  16x16  |  16x16  |
| `ICON_SIZE_SMALL`       |  32x32  |  32x32  |
| `ICON_SIZE_MEDIUM`      |  64x64  |  64x64  |
| `ICON_SIZE_LARGE`       | 256x256 | 256x256 |
| `ICON_SIZE_EXTRA_LARGE` | 256x256 | 512x512 |

### Functions

#### getIconForPath(path, size, callback)

Gets associated icon for file or folder path, and returns it in the PNG format.

#### getIconForExtension(extension, size, callback)

Gets associated icon for file extension, and returns it in the PNG format.

## License

MIT
