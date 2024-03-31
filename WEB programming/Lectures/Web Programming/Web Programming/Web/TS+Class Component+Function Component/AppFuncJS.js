// Two Fundamentals of React:
// 1. props
// 2. State

//Functional Component

import './App.css'
import { useState } from 'react'
function AppFunc(props) {
  const [name, SetName] = useState("");
  const [age, SetAge] = useState(25);
  const [isMale, setIsMale] = useState(true);
  return (
    <div>
    <h1>Hello World</h1>
        <h1>My name is {name}</h1>
        <h1>Iam {age} years old</h1>
        <h3>Iam {isMale ? "Male" : "Female"}</h3>
        <h4>Iam feeling {props.emotion}</h4>
    </div>
  )
}
export default AppFunc