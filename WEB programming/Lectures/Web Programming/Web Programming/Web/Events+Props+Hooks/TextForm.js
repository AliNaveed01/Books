import React , {useState} from 'react'

export default function TextForm(props) {
  const [text, setText] = useState('Text Input from useState');
  const handleClick = ()=>{
    let newText = text.toUpperCase();
    setText(newText);
    console.log("Ok button clicked");
  }

  const clearText = ()=>{
    let newText = " ";
    setText(newText);
  }
  const handleOnChange = (e)=>{
    setText(e.target.value);
    console.log("On Change");
  }
  //text = "xyz" wrong way to change the state
  //setText("xyz") correct way to change the state
  return (
    <div className='container'>
        <h1>{props.heading}</h1>
        <div className="mb-3">
        <label htmlfor="mybox" className="form-label"></label>
        <textarea className="form-control" value={text} onChange={handleOnChange} id="mybox" rows="8"></textarea>
        </div>
        <button className='btn-primary mx-1' onClick={handleClick}>OK</button>
        <button className='btn-primary mx-1' onClick={clearText}>Clear</button>
        <div className='container my-3'>
            <h1>Your Text Summary</h1>
            <p>{text.split(" ").length} words and {text.length} characters</p>
        </div>
    </div>
  );
}
