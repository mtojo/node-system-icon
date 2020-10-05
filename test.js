const system = require("./index");
const {writeFileSync} = require('fs');

// const {getIconForPath, ICON_SIZE_MEDIUM} = require('system-icon');


system.getIconForPath("/Applications/Brave Browser.app", system.ICON_SIZE_MEDIUM, (err, result) => {
    if (err) {
        console.error(err);
    } else {
        writeFileSync("icon.png", result);
    }
});
