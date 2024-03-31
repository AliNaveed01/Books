import React , {useState} from 'react';

export default function Counter() {

  const [count, setCount] = useState(0);
  const [state, setState] = useState({num:4, theme:'blue'});
  const num = state.num
  const theme = state.theme

  function decrementCount() {
    // setCount(count - 1);
    // setCount(count - 1);

    //setCount(preCount => preCount - 1);
    setCount(preCount => preCount - 1);
    setState(preState => {
      return {count: preState.num - 1}
    })
  }

  function incrementCount() {
    setCount(preCount => preCount + 1);
  }

  return (
    <>
      <button onClick={decrementCount}>-</button>
      <span>{count}</span>
      <span>{num}</span>
      <span>{theme}</span>
      <button onClick={incrementCount}>+</button>
    </>
  );
}

