var d = 134


function drawCircles() {
    var x = 10;
    var y = 10;
    for (var i = 0; i < 5; i++) {
        span = document.createElement('span');
        span.className = "circle";
        span.style.left = x + 'px';
        span.style.top = y + 'px';
        document.body.appendChild(span);
        x += d + 4;
    }

}

drawCircles()