const d = 134;
const r = d / 2;

var pageColors = {};

function tglLabel() {
    if (window.label) {
        var labels = document.querySelectorAll(".label");
        labels.forEach(label => {
            label.style.display = "none";
        })
        window.label = false;
    } else {
        var labels = document.querySelectorAll(".label");
        labels.forEach(label => {
            label.style.display = "block";
        })
        window.label = true;
    }
}

function getColor(color) {
    return `${color[0]},${color[1]},${color[2]}`;
}

function drawCircles() {
    var x = 15;
    var y = 0;

    k = 0;
    var colors = pageColors[document.title];

    for (var i = 0; i < 4; i++) {
        for (var j = 0; j < 5; j++) {
            div = document.createElement('div');
            div.className = "circle";
            div.style.left = x + 'px';
            div.style.top = y + 'px';

            var color = getColor(colors[k++]);
            div.style.backgroundColor = `rgb(${color})`;

            var label = document.createElement('span');
            label.className = "label";
            // label.textContent = (k - 1) + ')' + color;
            label.textContent = color;
            div.appendChild(label);

            document.body.appendChild(div);
            x += d + 4;
        }
        y += d - 14
        x -= r + d + 6
        for (var j = 0; j < 4; j++) {
            div = document.createElement('div');
            div.className = "circle";
            div.style.left = x + 'px';
            div.style.top = y + 'px';

            var color = getColor(colors[k++]);
            div.style.backgroundColor = `rgb(${color})`;

            var label = document.createElement('span');
            label.className = "label";
            // label.textContent = (k - 1) + ')' + color;
            label.textContent = color;
            div.appendChild(label);

            document.body.appendChild(div);
            x -= d + 4;
        }
        y += d - 14
        x += r + 4
    }
}

function spliceIntoChunks(arr, chunkSize) {
    var i = 0;
    while (arr.length > 0) {
        const chunk = arr.splice(0, chunkSize);
        pageColors[i] = chunk;
        i++;
    }
}

function genColors() {

    values = [0, 64, 128, 192, 255];
    colors = [];

    for (var r = 0; r < 5; r++) {
        for (var g = 0; g < 5; g++) {
            for (var b = 0; b < 5; b++) {
                colors.push([values[r], values[g], values[b]]);
            }
        }
    }

    while (colors.length < 144)
        colors.push([255, 255, 255])

    spliceIntoChunks(colors, 36);

    console.log(pageColors[document.title]);
}

function arr_sum(arr) {
    s = 0;

    for (var i = 0; i < 3; i++)
        s += arr[i];

    if (s < 10) s = 0;
    return s;
}

function arr_sub(arr1, arr2) {

    for (var i = 0; i < 3; i++) {
        t = arr1[i] - arr2[i];
        if (t < 0) t = 0;
        arr1[i] = Math.round(t);
    }

}

function logColorAsArray(colors) {
    var arrStr="{\n";
    colors.forEach(color => {
        arrStr+=(`{${color[0]}, ${color[1]}, ${color[2]}},\n`)
    });
    arrStr+="};"
    console.log(arrStr);
}

function genRainBow() {
    rainbow = [
        [255, 0, 0],
        [255, 127, 0],
        [255, 255, 0],
        [0, 255, 0],
        [0, 0, 255],
        [75, 0, 130],
        [148, 0, 211],
        [255, 255, 255]
    ];

    var colors = [];

    var n = 5;
    for (var i = 0; i < 8; i++) {
        var dec = [];
        for (var j = 0; j < 3; j++) {
            dec.push(rainbow[i][j] / n);
        }
        var color = rainbow[i];

        while (arr_sum(color)) {
            colors.push([...color]);
            arr_sub(color, dec);
        }

    }

    var basicIndices = [0, 15, 20, 35];

    basicIndices.forEach(i => {
        colors[i] = null;
    });

    colors = colors.filter(function (el) {
        return el != null;
    });

    logColorAsArray(colors);
    pageColors[0] = colors;

}

// genColors();
genRainBow();
drawCircles();