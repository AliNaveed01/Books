import React, { Component } from 'react';

interface AppClassProps {
  emotion: string;
}

interface AppClassState {
  name: string;
  age: number;
  isMale: boolean;
}

class AppClass extends Component<AppClassProps, AppClassState> {
  constructor(props: AppClassProps) {
    super(props);
    this.state = {
      name: " ",
      age: 100,
      isMale: true,
    };
  }

  componentDidMount() {
    this.setState({
      name: "Saif"
    });
  }

  render() {
    const { name, age, isMale } = this.state;
    const { emotion } = this.props;

    return (
      <div>
        <h1>Hello World</h1>
        <h1>My name is {name}</h1>
        <h1>I am {age} years old</h1>
        <h3>I am {isMale ? "Male" : "Female"}</h3>
        <h4>I am feeling {emotion}</h4>
      </div>
    );
  }
}

export default AppClass;
