using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class SymbolInput : MonoBehaviour
{
    [SerializeField] Text symbolInputText;

    private void Start()
    {
        ResetText();
    }

    public void ResetText()
    {
        symbolInputText.text = string.Empty;
    }

    public void AddText(string text)
    {
        symbolInputText.text += text;
    }

    public void SendText()
    {
        ResetText();
        // how tf bro
    }
}
