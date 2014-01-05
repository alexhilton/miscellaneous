function showWarn(msg) {
    alert(msg);
}

function doAlert(msg) {
    alert(msg);
}

/**
 * Factorial of an positive integer.
 * Just to prove that JavaScript supports recusion.
 */
function factor(num) {
    if (num < 2) {
        return num;
    }
    return num * factor(num - 1);
}

/**
 * Summon.
 */
function sum(num) {
    var s = 0;
    for (var i = 1; i <= num; i++) {
        s += i;
    }
    return s;
}

/**
 * Add objects to document.
 */
function addObjects() {
    var star = {};
    star["Polaris"] = new Object;
    star["Mizar"] = new Object;
    star["Aldebaran"] = new Object;
    star["Rigel"] = new Object;

    star["Polaris"].constellation = "Ura Minor";
    star["Mizar"].constellation = "Usra Major";
    star["Aldebaran"].constellation = "Taurus";
    star["Rigel"].constellation = "Orion";

    delete star["Polaris"].constellation;
    for (starName in star) {
        var para = document.createElement("p");
        para.id = starName;
        para.appendChild(document.createTextNode(starName + ": " + star[starName].constellation));
        document.getElementsByTagName("body")[0].appendChild(para);
    }
}

function sumObjects() {
    var age = {
        "kevin" : 21,
        "lee" : 30,
        "sou" : 40,
        "max" : 20,
        "liu" : 10,
        "shane" : 19
    };

    var sum = 0;
    for (var i in age) {
        sum += age[i];
    }
    return sum;
}

function addObjects2() {
    var star = new Object;
    star.name = "Polaris";
    star.type = "Double/Cepheid";
    star.constellation = "Ursa Minor";

    var sum;
    for (var s in star) {
        sum += s;
    }
    return sum;
}

function responseName(name) {
    switch (name) {
    case "alex":
        return "Welcome alex";
    case "Steve":
        return "go away";
    default:
        return "Please come back later";
    }
}

function annymousArguments() {
    var a1 = arguments[0];
    var a2 = arguments[1];
    console.log("a1 is " + a1);
    console.log("a2 is " + a2);
}

function promptExit() {
    var opt = window.confirm("Do you really want to exit?");
    if (opt) {
        console.log("exiting");
    } else {
        console.log("remain in the same page");
    }
}

function iterateObjects() {
    var star = {};
    star["Polaris"] = new Star("Uras minor", "Double/Cepheid", "F7", 2.0);
    star["Mizar"] = new Star("Ursa Major", "Spectraoscop", "A1v", 2.3);
    star["Aldebaran"] = new Star("Taurus", "Irregular Variable", "K5", 0.85);
    star["Rigel"] = new Star("Orion", "Supergiant with Compaign", "b8", 0.12);

    for (var propt in star) {
        console.log(star[propt].toString());
    }

    var names = [];
    for (var index in star) {
        names.push(index);
    }
    console.log(names.join(":"));
}

function Star(cons, type, spec, mag) {
    this.constellation = cons;
    this.type = type;
    this.spectralClass = spec;
    this.mag = mag;
    this.toString = function() {
        return "constellation: " + this.constellation + ", type: " + this.type + ", spec: " + this.spectralClass + ", mag: " + this.mag;
    }
}

function iterateArrays() {
    var star = ["Venus", "Earth", "Mars", "Saturn", "Pluto"];
    star.push("Syrus");
    star = star.concat("Sun");
    star.unshift("Friends");
    for (var index in star) {
        console.log(star[index]);
    }
}

function anatomyDate() {
    var today = new Date();
    console.log(today.toLocaleDateString());
    console.log("day " + today.getDate() + " of the month");
    console.log("day " + today.getDay() + " of the week");
}

function exploringWindow() {
    console.log(window.name);
    window.resizeTo(600, 480);
    console.log(" ava width " + window.screen.availWidth);
    console.log(" width " + window.screen.width);
    console.log(" ava height " + window.screen.availHeight);
    console.log(" height " + window.screen.height);
    if (screen.width != 1024 || screen.height != 768) {
        alert("This app must run in 1024 * 768");
    }

    for (var prop in navigator) {
        console.log(navigator[prop]);
    }
}

function theDom() {
    var p = document.getElementById("result");
    p.innerHTML = "what the fuck";
    p.style.background = "#ffff00";
    var links = document.getElementsByTagName("a");
    console.log("links.len " + links.length);
    for (var i = 0; i < links.length; i++) {
        links[i].style.background = "#ffff00";
        console.log(links[i].href);
        var attrs = [];
        for (var attr in links[i]) {
            attrs.push(links[i].getAttribute(attr));
        }
        //console.log(attrs.join("\n"));
    }
    var la = document.getElementById("la");
    la.setAttribute("href", "https://www.twitter.com/tw/");
    la.setAttribute("target", "_blank");

    // create a paragraph and link
    var p = document.createElement("p");
    p.innerHTML = "I am created from JavaScript code";
    p.setAttribute("id", "p_from");
    p.style.background = "#f000ff";
    document.body.appendChild(p);
    var br = document.createElement("br");
    document.body.appendChild(br);
    var hr = document.createElement("hr");
    document.body.appendChild(hr);
    var link = document.createElement("a");
    link.setAttribute("href", "https://www.google.com.hk/");
    link.setAttribute("id", "li");
    link.setAttribute("target", "_blank");
    link.style.background = "#990000";
    document.body.appendChild(link);
    link.appendChild(document.createTextNode("I am created from code"));

    document.body.removeChild(hr);
    document.body.appendChild(document.createElement("hr"));
    document.body.appendChild(document.createTextNode("The following is a table created from JavaScript"));
    createTable();
}

function createTable() {
    var tab = document.createElement("table");
    tab.setAttribute("id", "mytab");
    tab.setAttribute("border", 1);
    var row1 = document.createElement("tr");
    var c1 = document.createElement("td");
    c1.setAttribute("id", "cell1");
    c1.innerHTML = "Apple";
    row1.appendChild(c1);
    var c2 = document.createElement("td");
    c2.setAttribute("id", "cell2");
    c2.innerHTML = "Google";
    row1.appendChild(c2);
    tab.appendChild(row1);

    var row2 = document.createElement("tr");
    var c3 = document.createElement("td");
    c3.setAttribute("id", "cell3");
    c3.innerHTML = "iOS";
    row2.appendChild(c3);
    var c4 = document.createElement("td");
    c4.setAttribute("id", "cell4");
    c4.innerHTML = "Android";
    row2.appendChild(c4);
    tab.appendChild(row2);
    document.body.appendChild(tab);
}

function analyzeInsurance() {
    var capital = 4420;
    var interest = 0.03; // 3%
    var year = 20;
    var startYear = 23;
    var endYear = 43;
    var finalYear = 66;
    var c = 1 + interest;
    // every year deposite 4420, up to 20 years with interest 0.03
    var sum = 0;
    for (var n = 1; n <= year; n++) {
        sum += capital * Math.pow(c, n);
    }

    sum *= Math.pow(c, (finalYear - endYear));
    console.log("If no accidents, up to age 66, your paid money worth: " + sum);
    var insuranceValue = 105070;
    console.log("While the value of insurance up to 66 is : " + insuranceValue);
    console.log("You will at least lose money: " + (sum - insuranceValue));

    var oneYear = capital + capital * interest;
    console.log("You already paid : " + oneYear);
    console.log("you can get 420, if you quit now, loss is at most: " + (oneYear - 420));
    console.log("Year    Age        Illness            Death        Paid");
    var base = 100000;
    var rateIllness = 0.03;
    var rateDeath = 0.01;
    console.log("#%02d      %2d         %7f            %7f            %7f", 0, 23, 14420, 14420, 4420);
    var step = 1;
    for (var n = 1, age = 24; n <= 77; n += step, age += step) {
        console.log("#%02d      %2d         %7f            %7f            %7f", n, age, 
                Math.round(base * (1+rateIllness * n)), Math.round(base * (1+rateDeath *n)), Math.round(getPaid(n)));
    }
    console.log("Compare this table with the insurance value table you can learn the essence of insurance and insurance business");
    console.log("1. Why they say after age 66 you can take insurance value as pension, because your paid money is 241429, while the maximum compensation is 229000, compensation is less that your paid money; In fact, when after age 65 your paid money is greater than maximium compensation.");
    console.log("2. Pension is part of compensation, which means, if you take pension, your maximium compensation is substracted, too.");
    console.log("3. By this table, we learn that if you have diseases before age 65, this insurance profits and the earlier you have disease the greater benifits is;");
    console.log("4. After age 65, no matter how big your diseases are, you lose money.");
    console.log("5. If you do not have disease or accident death, you have maximium loss");
    console.log("From last five points, we learn that The candidates customers of this kind of insurance are young men, which are much healthier and stronger and safer in first two or three decades. Because, within first two decades insurance will pay more than your fees. And after three decades, your paid money worth more than maximium compensation. So insurance company won't lose anything even though they pay you promised compensation. For a man, his body is stronger and healthier before his 40's or 50's. After age of 60's or 70's, body begins decaying and so comes diseases but up to that age, your paid money is already worth more than maximium compensation. Insurance company won't lose anything. Of course, if insurance company are so unlucky that everybody insured get sick or killed when they are young, all companies would bankrupt for they cannot afford the compensations, which is not likely to happen in reality.");
    console.log("In all, this kind of insurance is for insurance company, not for customers. For most customers, they will lose money and cannot get necessary guarantee because compensation is less");
    console.log("We have to terminate the contract immediately!");
}

function getPaid(year) {
    var capital = 4420;
    var interest = 0.03;
    var span = 20;
    var c = 1 + interest;
    var sum = 0;
    if (year <= span) {
        for (var n = 1; n <= year; n++) {
            sum += capital * Math.pow(c, n);
        }
        return sum;
    }
    sum = 0;
    for (var n = 1; n <= span; n++) {
        sum += capital * Math.pow(c, n);
    }
    sum *= Math.pow(c, (year - span));
    return sum;
}

function testCookie() {
    if (navigator.cookieEnabled) {
        var tst = new Array();
        tst[0] = "hello";
        tst[1] = "there";
        setCookie("doc", document);
        /*var sum = readCookie("sum");
        var isum = 0;
        if (sum) {
            isum = parseInt(sum) + 1;
            if (isum > 10) {
                eraseCookie("sum");
            } else {
                setCookie("sum", isum);
            }
        } else {
            setCookie("sum", 0);
        }*/
    } else {
        console.log("oops, to see the result, please enable cookie on your browser");
    }
    console.log(document.cookie);
}

function setCookie(key, value) {
    var cookieDate = new Date(2012, 11, 29, 19, 30, 30);
    document.cookie = key + "=" + escape(value) + "; expires=" + cookieDate.toGMTString() + "; path=/";
    console.log(document.cookie);
}

function readCookie(key) {
    var cookie = document.cookie;
    var first = cookie.indexOf(key + "=");
    if (first >= 0) {
        var str = cookie.substring(first, cookie.length);
        var last = str.indexOf(";");
        if (last < 0) {
            last = str.length;
        }
        str = str.substring(0, last).split("=");
        return unescape(str[1]);
    } else {
        return null;
    }
}

function eraseCookie(key) {
    var cookieDate = new Date(2002, 10, 11, 22, 30, 30);
    document.cookie = key + "=; expires=" + cookieDate.toGMTString() + "; path=/";
}

function writeX(evnt) {
    console.log("capturing: " + evnt.target + " " + evnt.currentTarget);
    alert("capturing: " + evnt.target + " " + evnt.currentTarget);
    return true;
}

function writeY(evnt) {
    console.log("bubbling: " + evnt.target + " " + evnt.currentTarget);
    alert("bubbling: " + evnt.target + " " + evnt.currentTarget);
    return true;
}

function setup(evnt) {
    document.addEventListener('click', writeX, true);
    document.forms[0].addEventListener('click', writeX, true);
    document.forms[0].elements[0].addEventListener('click', writeX, true);
    document.addEventListener('click', writeY, false);
    document.forms[0].addEventListener('click', writeY, false);
    document.forms[0].elements[0].addEventListener('click', writeY, false);
}
