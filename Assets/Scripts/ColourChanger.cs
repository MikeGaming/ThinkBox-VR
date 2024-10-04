using UnityEngine;

public class ColourChanger : MonoBehaviour
{

    private Material material;
    private bool isGreen;

    private void Start()
    {
        material = GetComponent<Renderer>().material;
    }

    public void ChangeColour()
    {
        isGreen = !isGreen;
        if (isGreen)
        {
            material.color = Color.green;
        }
        else
        {
            material.color = Color.white;
        }
    }
}
