import "./App.css"
// import CountClassComp from "./Components/CountClassComp";
// import FuncComponent from "./Components/FuncComponent";
import Navbar from './Components/Navbar';
import TextForm from "./Components/TextForm";
import Counter from "./Components/Counter";

function App() {
  return (
  <>
    <Navbar/>
    <TextForm heading="Word Count"></TextForm>
    {/* <Counter></Counter> */}
    {/* <FuncComponent></FuncComponent> */}
    {/* <CountClassComp></CountClassComp> */}
  </>
    
  )
}

export default App;

