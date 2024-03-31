import * as actions from './actionsTypes.js'
let lastId = 0;

export default function reducer(state = [], action){
    switch (action.type){
        case actions.BOOK_ADDED:
            return [
                ...state,
                {
                    id: ++lastId,
                    name: action.payload.name,
                    resolved: false
                }
            ];
        case actions.BOOK_REMOVED:
            return state.filter(book => book.id !== action.payload.id);
        case actions.BOOK_UPDATED:
            return state.map(book => book.id !== action.payload.id ? 
                book : {...book, resolved:true}) 
        default:    
            return state;
    }   
}