const char* mainPageContent = R"(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Simple ESP8266 Web Page</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            padding: 20px;
            background-color: #f0f2f5;
            color: #333;
        }
        h1 {
            color: #333;
            text-align: center;
        }
        p {
            line-height: 1.6;
        }
        a {
            color: #007bff;
            text-decoration: none;
        }
        .relay-control {
            display: flex;
            align-items: center;
            margin-bottom: 10px;
        }
        .relay-label {
            flex: 1;
            font-size: 16px;
            color: #333;
        }
        .button {
            padding: 10px 20px;
            font-size: 14px;
            cursor: pointer;
            text-align: center;
            text-decoration: none;
            outline: none;
            color: #fff;
            background-color: #007bff;
            border: none;
            border-radius: 5px;
            margin-left: 10px;
            transition: background-color 0.3s, box-shadow 0.3s;
        }
        .button:hover {
            background-color: #0056b3;
        }
        .button:active {
            background-color: #004494;
            box-shadow: 0 5px #666;
            transform: translateY(4px);
        }
    </style>
</head>
<body>
    <h1>Welcome to ESP8266 Web Server</h1>
    <p>This is a simple HTML page served by ESP8266.</p>
    <p>You can add more content here.</p>
    <p>For example, you can create links:
        <a href="/other-page">Go to Another Page</a>
    </p>
    <h1>Relay Control</h1>
)";

const char* buttonScript = R"(
        <script>
        function sendPost(pin, state) {
            var xhr = new XMLHttpRequest();
            var url = "/relays";
            xhr.open("POST", url, true);
            xhr.setRequestHeader("Content-Type", "application/json");
            xhr.onreadystatechange = function () {
                if (xhr.readyState === 4 && xhr.status === 200) {
                    var json = JSON.parse(xhr.responseText);
                    alert(json.message);
                    location.reload(); // Refresh the page
                }
            };
            var data = JSON.stringify({"pin": pin, "state": state});
            xhr.send(data);
        }
        </script>
)";
