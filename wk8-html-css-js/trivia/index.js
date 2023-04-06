
let form1 = document.querySelector('#form-1');
let form2 = document.querySelector('#form-2');

form1.addEventListener('submit', function(event){
    let fb1 = document.querySelector('#fb-1');
    let input1 = document.querySelector('#input-1');
    event.preventDefault();
    if(!form1.classList.contains('fb-present'))
    {
        form1.classList.add('fb-present');
        if (input1.value.toLowerCase() == 'phoenix')
        {
            fb1.innerHTML = "Correct!";
            input1.style.backgroundColor = 'limegreen';
        }
        else
        {
            fb1.innerHTML = "Incorrect.";
            input1.style.backgroundColor = 'indianred';
        }
    }
    else return;
});

form2.addEventListener('submit', function(event){
    let fb2 = document.querySelector('#fb-2');
    let input2 = document.querySelector('#input-2');
    event.preventDefault();
    if(!form2.classList.contains('fb-present'))
    {
        form2.classList.add('fb-present');
        if (input2.value.toLowerCase() == 'gold')
        {
            fb2.innerHTML = "Correct!";
            input2.style.backgroundColor = 'limegreen';
        }
        else
        {
            fb2.innerHTML = "Incorrect.";
            input2.style.backgroundColor = 'indianred';
        }
    }
    else return;
});

let correctButtons = document.querySelectorAll('.button-correct');
let incorrectButtons = document.querySelectorAll('.button-incorrect');

for (let corrButton of correctButtons)
{
    corrButton.addEventListener('click', function()
    {
        let container1 = document.querySelector('.question-1');
        let container2 = document.querySelector('.question-2');
        if (corrButton.classList.contains('q-1')){
            if(!container1.classList.contains('fb-present'))
            {
                container1.classList.add('fb-present');
                corrButton.style.backgroundColor = 'limegreen'
                let feedback = document.createElement('p');
                feedback.innerHTML = 'Correct!';
                container1.append(feedback);
            }
            else return;
        }
        else {
            if(!container2.classList.contains('fb-present'))
            {
                container2.classList.add('fb-present');
                corrButton.style.backgroundColor = 'limegreen';
                let feedback2 = document.createElement('p');
                feedback2.innerHTML = 'Correct!';
                container2.append(feedback2);
            }
            else return;
        }
    })
}

for (let incorrButton of incorrectButtons)
{
    incorrButton.addEventListener('click', function()
    {
        let container1 = document.querySelector('.question-1');
        let container2 = document.querySelector('.question-2');
        if (incorrButton.classList.contains('q-1'))
        {
            if(!container1.classList.contains('fb-present'))
            {
                container1.classList.add('fb-present');
                incorrButton.style.backgroundColor = 'indianred';
                let feedback = document.createElement('p');
                feedback.innerHTML = 'Incorrect.';
                container1.append(feedback);
            }
            else return;
        }
        else
        {
            if(!container2.classList.contains('fb-present'))
            {
                container2.classList.add('fb-present');
                incorrButton.style.backgroundColor = 'indianred';
                let feedback2 = document.createElement('p');
                feedback2.innerHTML = 'Incorrect.';
                container2.append(feedback2);
            }
            else return;
        }
    })
}