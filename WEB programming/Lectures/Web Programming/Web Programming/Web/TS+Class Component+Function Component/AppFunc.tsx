import React, { useState } from 'react';

interface AppFuncProps {
  emotion: string;
}

function AppFunc(props: AppFuncProps) {
  const [name, setName] = useState("");
  const [age, setAge] = useState(25);
  const [isMale, setIsMale] = useState(true);

  return (
    <div>
      <h1>Hello World</h1>
      <h1>My name is {name}</h1>
      <h1>I am {age} years old</h1>
      <h3>I am {isMale ? "Male" : "Female"}</h3>
      <h4>I am feeling {props.emotion}</h4>
    </div>
  );
}

export default AppFunc;
