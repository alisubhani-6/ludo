let boxes = document.querySelectorAll(".box");
let dice = document.querySelector(".dice");
let dice_box = document.querySelector(".dice-box h2");

const safe = [1,14,23,24,39,52,65,66];

const blue = [63, 60, 57, 54, 17, 16, 15, 14, 13, 12,6, 0, 1, 2, 3, 4, 5, 33, 30, 27,24, 21, 18, 19, 20, 23, 26, 29, 32, 35,36, 37, 38, 39, 40, 41, 47, 53, 52, 51,50, 49, 48, 56, 59, 62, 65, 68, 71, 70,67, 64, 61, 58, 55];
const red = [2, 3, 4, 5, 33, 30, 27, 24, 21, 18, 19, 20, 23, 26, 29, 32,35, 36, 37, 38, 39, 40, 41, 47, 53, 52, 51, 50, 49, 48, 56,59, 62, 65, 68, 71, 70, 69, 66, 63, 60, 57, 54, 17, 16, 15,14, 13, 12, 6, 7, 8, 9, 10, 11];
const green = [26, 29, 32, 35, 36, 37, 38, 39, 40, 41,47, 53, 52, 51, 50, 49, 48, 56, 59, 62,65, 68, 71, 70, 69, 66, 63, 60, 57, 54,17, 16, 15, 14, 13, 12, 6, 0, 1, 2,3, 4, 5, 33, 30, 27, 24, 21, 18, 19,22, 25, 28, 31, 34];
const yellow = [51, 50, 49, 48, 56, 59, 62, 65, 68, 71,70, 69, 66, 63, 60, 57, 54, 17, 16, 15,14, 13, 12, 6, 0, 1, 2, 3, 4, 5,33, 30, 27, 24, 21, 18, 19, 20, 23, 26,29, 32, 35, 36, 37, 38, 39, 40, 41, 47,46, 45, 44, 43, 42];


class Bot {
    constructor(path) {
        this.path = path;
        this.position = -1; 
        this.finished = false;
    }
}

class Player {
    constructor(name, home, color, path) {
        this.name = name;
        this.home = home;
        this.color = color;
        this.bots = [new Bot(path), new Bot(path), new Bot(path), new Bot(path)];
        this.turn = false;
    }

    openedBots() {
        return this.bots.filter(bot => bot.position !== -1 && !bot.finished);
    }

    closedBots() {
        return this.bots.filter(bot => bot.position === -1);
    }
}


let player1 = new Player("Player 1", 66, "blue", blue);
player1.turn = true;
let player2 = new Player("Player 2", 1, "red", red);
let player3 = new Player("Player 3", 23, "green", green);
let player4 = new Player("Player 4", 52, "yellow", yellow);
let players = [player1, player2, player3, player4];


dice.addEventListener("click", () => {
    let roll = Math.floor(Math.random() * 6) + 1;
    dice.innerHTML = roll;

    let currentPlayer = players.find(p => p.turn);
    movePlayer(currentPlayer, roll);
});


function nextTurn() {
    for (let i = 0; i < players.length; i++) {
        if (players[i].turn) {
            players[i].turn = false;
            players[(i + 1) % players.length].turn = true;
            dice_box.innerHTML = players[(i + 1) % players.length].name.toUpperCase();
            break;
        }
    }
}


function clearBoardHighlights() {
    boxes.forEach(box => {
        box.style.border = "";
        box.style.cursor = "default";
        box.onclick = null;
    });
}


function highlightBox(index) {
    boxes[index].style.border = "4px solid orange";
    boxes[index].style.cursor = "pointer";
}


function movePlayer(player, roll) {
    clearBoardHighlights();
    dice.disabled = true;

    let closedBots = player.closedBots();
    let openBots = player.openedBots();
    let moveAvailable = false;

    if (roll === 6 && closedBots.length > 0) {
        let botToOpen = closedBots[0];
        highlightBox(player.home);
        boxes[player.home].onclick = () => {
            botToOpen.position = 0;
            renderBots();
            clearBoardHighlights();
            dice.disabled = false;
            nextTurn();
        };
        moveAvailable = true;
    }

    openBots.forEach((bot, i) => {
        let nextPos = bot.position + roll;
        if (nextPos < bot.path.length) {
            let index = bot.path[nextPos];
            highlightBox(index);
            boxes[index].onclick = () => {
                let oldPos = bot.position;
                bot.position = nextPos;
                handleCapture(player, bot, oldPos);
                renderBots();
                clearBoardHighlights();
                dice.disabled = false;
                nextTurn();
            };
            moveAvailable = true;
        }
    });

    if (!moveAvailable) {
        dice.disabled = false;
        nextTurn();
    }
}


function handleCapture(player, bot, oldPos) {
    let index = bot.path[bot.position];
    if (safe.includes(index)) return;

    players.forEach(p => {
        if (p.color !== player.color) {
            p.bots.forEach(b => {
                if (b.position !== -1 && b.path[b.position] === index) {
                    b.position = -1;
                    b.finished = false;
                }
            });
        }
    });
}


function renderBots() {
    boxes.forEach(box => box.textContent = "");

    players.forEach(player => {
        player.bots.forEach((bot, i) => {
            if (bot.position !== -1 && !bot.finished) {
                let index = bot.path[bot.position];
                if (boxes[index].textContent === "") {
                    boxes[index].textContent = i;
                    boxes[index].style.color = player.color;
                } else {
                    if (!safe.includes(index)) {
                        let otherPlayer = players.find(p => p.color !== player.color && p.bots.some(b => b.path[b.position] === index));
                        if (otherPlayer) {
                            let otherBot = otherPlayer.bots.find(b => b.path[b.position] === index);
                            otherBot.position = -1;
                            otherBot.finished = false;
                        }
                        boxes[index].textContent = i;
                        boxes[index].style.color = player.color;
                    } else {
                        boxes[index].textContent += "," + i;
                    }
                }
            }
        });
    });
}
