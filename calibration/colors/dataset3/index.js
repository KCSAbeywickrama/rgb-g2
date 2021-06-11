const d = 100;
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

function drawCircles() {
    var x = 44;
    var y = 70;

    k = 0;
    var colors = pageColors[0];

    for (var i = 0; i < 6; i++) {
        for (var j = 0; j < 7; j++) {
            div = document.createElement('div');
            div.className = "circle";
            div.style.left = x + 'px';
            div.style.top = y + 'px';

            var color = colors[k++];
            div.style.backgroundColor = `rgb(${color})`;

            var label = document.createElement('span');
            label.className = "label";           
            label.textContent = color;
            div.appendChild(label);

            var index = document.createElement('span');
            index.className = "index";
            index.textContent = (k - 1);
            div.appendChild(index);

            document.body.appendChild(div);
            x += d + 1;
        }

        if (k >= 72) return;

        y += d - 12
        x -= r + d + 2
        for (var j = 0; j < 6; j++) {
            div = document.createElement('div');
            div.className = "circle";
            div.style.left = x + 'px';
            div.style.top = y + 'px';

            var color = colors[k++];
            div.style.backgroundColor = `rgb(${color})`;

            var label = document.createElement('span');
            label.className = "label";
            label.textContent = color;
            div.appendChild(label);

            var index = document.createElement('span');
            index.className = "index";
            index.textContent = (k - 1);
            div.appendChild(index);

            document.body.appendChild(div);
            x -= d + 1;
        }
        y += d - 10
        x += r + 1
    }
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

function arr_add(arr1, arr2) {

    for (var i = 0; i < 3; i++) {
        t = arr1[i] + arr2[i];
        if (t > 255) t = 255;
        arr1[i] = Math.round(t);
    }

}

function arr_str(arr) {
    return `${arr[0]},${arr[1]},${arr[2]}`;
}

function logColorsAsArray(colors) {
    var arrStr = "{\n";
    colors.forEach(color => {
        arrStr += (`{${color[0]}, ${color[1]}, ${color[2]}},\n`)
    });
    arrStr += "};"
    console.log(arrStr);
}

function logColorsForPlot(colors) {
    var x = [];
    var y = [];
    var z = [];
    var csv = "";
    colors.forEach(color_str => {
        csv += color_str + "\n";
        var color = color_str.split(",");
        x.push(parseInt(color[0]));
        y.push(parseInt(color[1]));
        z.push(parseInt(color[2]));
    });

    var output = `r=${JSON.stringify(x)};\ng=${JSON.stringify(y)};\nb=${JSON.stringify(z)};\n`;

    console.log(output);
    console.log(csv);
}

function genColors() {
    rainbow = [
        [255, 0, 0],
        [0, 255, 0],
        [0, 0, 255],

        [255, 255, 0],
        [0, 255, 255],
        [255, 0, 255],

        [255, 165, 0],
        [128, 0, 128],
        [255, 255, 255]
    ];

    var colors_set = new Set(["255,255,255", "0,0,0",
        "255,0,0", "0,255,0", "0,0,255"]);

    var n1 = 5;
    var n2 = 4;

    for (var i = 0; i < 9; i++) {
        var color = rainbow[i];

        var dec = [];
        for (var j = 0; j < 3; j++) {
            dec.push(color[j] / n1);
        }

        var inc = [255, 255, 255];
        arr_sub(inc, color);
        for (var j = 0; j < 3; j++) {
            inc[j] /= n2;
        }

        var color_dec = [...color];
        var color_inc = [...color];

        var tmp_inc = [];
        while (arr_sum(color_inc) < 765) {
            tmp_inc.push(arr_str(color_inc));
            arr_add(color_inc, inc);
        }

        for (var j = tmp_inc.length - 1; j >= 0; j--)
            colors_set.add(tmp_inc[j]);

        while (arr_sum(color_dec)) {
            arr_sub(color_dec, dec);
            colors_set.add(arr_str(color_dec));
        }
    }

    colors_set.delete("51,33,0");

    var extra = ["50,150,150", "100,200,200", "220,60,120", "160,80,80"]

    pageColors[0] = [...colors_set, ...extra];

    console.log(colors_set)

    logColorsForPlot(pageColors[0]);
}

genColors();
drawCircles();