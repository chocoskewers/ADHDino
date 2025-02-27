var timerInterval;
var focustimes = "10"
var popupTimeout;

function startTimer() {
    var button = document.getElementById("startBtn")
    var timerElement = document.getElementById('timer');
    var time = 0.0;
    button.disabled = true;
    button.style.backgroundColor = "#2B5C8C";

    timerInterval = setInterval(function () {
    time += 0.1;
    timerElement.textContent = time.toFixed(1)
    if (time >= focustimes) {
        clearInterval(timerInterval);
        showPopup();
        }
    }, 100);
}

function changeSelect() {
    pausetimes = document.getElementById("pausetime").value;
    focustimes = document.getElementById("focustime").value;
    PaymentRequestUpdateEvent()
}

function showPopup() {
    var popupElement = document.getElementById('popupOverlay');
    var pausetimes = document.getElementById("pausetime").value
    playsoundpause();
    popupElement.style.display = 'block';
    popupTimeout = setTimeout(function () {
    resetTimer();
    hidePopup()
    }, pausetimes)
}

function hidePopup() {
    var popupElement = document.getElementById('popupOverlay');
    popupElement.style.display = 'none';
    playsoundfocus();
}

function playsoundpause() {
    var audioElement = new Audio ("../../media/testaudiopause.mp3")
    audioElement.play()
}
function playsoundfocus() {
    var audioElement = new Audio ("../../media/testaudiofocus.wav")
    audioElement.play()
}
function resetTimer() {
    var timerElement = document.getElementById('timer');

    //hidePopup();
    clearInterval(timerInterval);
    clearTimeout(popupTimeout);
    timerElement.textContent = '0.0';
    startTimer();
}