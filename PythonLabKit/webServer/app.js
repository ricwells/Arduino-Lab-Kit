function doFetch(request) {
    if (request === undefined) {
        url = "/Data"
        const result2 = document.getElementById("divResults")
        fetch(url)
        // fetch() returns a promise. When we have received a response from the server,
        // the promise's `then()` handler is called with the response.
        .then((response) => {
            // Our handler throws an error if the request did not succeed.
            if (!response.ok) {
                throw new Error(`HTTP error: ${response.status}`);
            }
            // Otherwise (if the response succeeded), our handler fetches the response
            // as text by calling response.text(), and immediately returns the promise
            // returned by `response.text()`.
            t = response.text();
            return t;
        })
        // When response.text() has succeeded, the `then()` handler is called with
        // the text, and we copy it into the `poemDisplay` box.
        .then((text) => {
            result2.textContent = text;
            setInterval(doFetch, 2000);
        })
        // Catch any errors that might happen, and display a message
        // in the `poemDisplay` box.
        .catch((error) => {
            //result2.textContent = `Could not fetch data: ${error}`;
        })
    }
    else {
        url = request
        fetch(url, {
            method: 'POST'
        })
        doFetch()
    }
}
