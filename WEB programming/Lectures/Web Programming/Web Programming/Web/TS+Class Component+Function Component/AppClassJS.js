import React from 'react';
class AppClass extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      name: " ",
      age: 27,
      isMale: true,
    };
  }

  render() {

    this.setState({
        name: "Saif"
    })

    const { name, age, isMale } = this.state;
    const { emotion } = this.props;
    return (
        <div>
        <h1>Hello World</h1>
        <h1>My name is {name}</h1>
        <h1>Iam {age} years old</h1>
        <h3>Iam {isMale ? "Male" : "Female"}</h3>
        <h4>Iam feeling {emotion}</h4>
    </div>
    )
  }
}
export default AppClass;