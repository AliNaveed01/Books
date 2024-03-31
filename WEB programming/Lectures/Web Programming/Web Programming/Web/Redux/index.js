import store from "./store.js";
import { bookAdded, bookUpdated, bookRemoved } from "./actions.js";
import * as actions from './actionsTypes.js';

// console.log(store.getState());
// console.log(store);

const unsubscribe = store.subscribe(() => {
    console.log("Store changed!", store.getState());
})

store.dispatch(bookAdded("Robinson Crusoe"));
// unsubscribe();
 store.dispatch(bookUpdated(1));
 store.dispatch({
    type:"bookRemoved",
    payload: { id:1 }
})
// console.log(store.getState()); 
// unsubscribe();
store.dispatch({
    type: actions.BOOK_ADDED,
    payload: { name: "Walking on water"}
});


// store.dispatch(bookRemoved(1));



// console.log("DDD" + store.getState());